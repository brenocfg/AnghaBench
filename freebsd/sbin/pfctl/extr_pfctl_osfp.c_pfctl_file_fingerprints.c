#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fp_subtype_nm; int /*<<< orphan*/  fp_version_nm; int /*<<< orphan*/  fp_class_nm; int /*<<< orphan*/  fp_enflags; } ;
struct pf_osfp_ioctl {int fp_ttl; int fp_flags; int fp_wsize; int fp_psize; int fp_wscale; int fp_mss; int fp_optcnt; TYPE_1__ fp_os; int /*<<< orphan*/  fp_tcpopts; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
typedef  int /*<<< orphan*/  pf_tcpopts_t ;
typedef  int /*<<< orphan*/  fp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ GET_INT (int,int*,char*,int,int) ; 
 scalar_t__ GET_STR (char*,char*,int) ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_VERBOSE2 ; 
 int PF_OSFP_DF ; 
 int /*<<< orphan*/  PF_OSFP_GENERIC ; 
 int PF_OSFP_INET6 ; 
 int PF_OSFP_MSS_DC ; 
 int PF_OSFP_MSS_MOD ; 
 int /*<<< orphan*/  PF_OSFP_NODETAIL ; 
 int PF_OSFP_PSIZE_DC ; 
 int PF_OSFP_PSIZE_MOD ; 
 int PF_OSFP_TS0 ; 
 int PF_OSFP_WSCALE_DC ; 
 int PF_OSFP_WSCALE_MOD ; 
 int PF_OSFP_WSIZE_DC ; 
 int PF_OSFP_WSIZE_MOD ; 
 int PF_OSFP_WSIZE_MSS ; 
 int PF_OSFP_WSIZE_MTU ; 
#define  T_DC 131 
#define  T_MOD 130 
#define  T_MSS 129 
#define  T_MTU 128 
 int /*<<< orphan*/  add_fingerprint (int,int,struct pf_osfp_ioctl*) ; 
 int /*<<< orphan*/  classes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int fingerprint_count ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_tcpopts (char const*,int,char*,int /*<<< orphan*/ *,int*,int*,int*,int*,int*,int*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memset (struct pf_osfp_ioctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_clear_fingerprints (int,int) ; 
 int /*<<< orphan*/  pfctl_flush_my_fingerprints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pfctl_fopen (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
pfctl_file_fingerprints(int dev, int opts, const char *fp_filename)
{
	FILE *in;
	char *line;
	size_t len;
	int i, lineno = 0;
	int window, w_mod, ttl, df, psize, p_mod, mss, mss_mod, wscale,
	    wscale_mod, optcnt, ts0;
	pf_tcpopts_t packed_tcpopts;
	char *class, *version, *subtype, *desc, *tcpopts;
	struct pf_osfp_ioctl fp;

	pfctl_flush_my_fingerprints(&classes);

	if ((in = pfctl_fopen(fp_filename, "r")) == NULL) {
		warn("%s", fp_filename);
		return (1);
	}
	class = version = subtype = desc = tcpopts = NULL;

	if ((opts & PF_OPT_NOACTION) == 0)
		pfctl_clear_fingerprints(dev, opts);

	while ((line = fgetln(in, &len)) != NULL) {
		lineno++;
		if (class)
			free(class);
		if (version)
			free(version);
		if (subtype)
			free(subtype);
		if (desc)
			free(desc);
		if (tcpopts)
			free(tcpopts);
		class = version = subtype = desc = tcpopts = NULL;
		memset(&fp, 0, sizeof(fp));

		/* Chop off comment */
		for (i = 0; i < len; i++)
			if (line[i] == '#') {
				len = i;
				break;
			}
		/* Chop off whitespace */
		while (len > 0 && isspace(line[len - 1]))
			len--;
		while (len > 0 && isspace(line[0])) {
			len--;
			line++;
		}
		if (len == 0)
			continue;

#define T_DC	0x01	/* Allow don't care */
#define T_MSS	0x02	/* Allow MSS multiple */
#define T_MTU	0x04	/* Allow MTU multiple */
#define T_MOD	0x08	/* Allow modulus */

#define GET_INT(v, mod, n, ty, mx) \
	get_int(&line, &len, &v, mod, n, ty, mx, fp_filename, lineno)
#define GET_STR(v, n, mn) \
	get_str(&line, &len, &v, n, mn, fp_filename, lineno)

		if (GET_INT(window, &w_mod, "window size", T_DC|T_MSS|T_MTU|
		    T_MOD, 0xffff) ||
		    GET_INT(ttl, NULL, "ttl", 0, 0xff) ||
		    GET_INT(df, NULL, "don't fragment frag", 0, 1) ||
		    GET_INT(psize, &p_mod, "overall packet size", T_MOD|T_DC,
		    8192) ||
		    GET_STR(tcpopts, "TCP Options", 1) ||
		    GET_STR(class, "OS class", 1) ||
		    GET_STR(version, "OS version", 0) ||
		    GET_STR(subtype, "OS subtype", 0) ||
		    GET_STR(desc, "OS description", 2))
			continue;
		if (get_tcpopts(fp_filename, lineno, tcpopts, &packed_tcpopts,
		    &optcnt, &mss, &mss_mod, &wscale, &wscale_mod, &ts0))
			continue;
		if (len != 0) {
			fprintf(stderr, "%s:%d excess field\n", fp_filename,
			    lineno);
			continue;
		}

		fp.fp_ttl = ttl;
		if (df)
			fp.fp_flags |= PF_OSFP_DF;
		switch (w_mod) {
		case 0:
			break;
		case T_DC:
			fp.fp_flags |= PF_OSFP_WSIZE_DC;
			break;
		case T_MSS:
			fp.fp_flags |= PF_OSFP_WSIZE_MSS;
			break;
		case T_MTU:
			fp.fp_flags |= PF_OSFP_WSIZE_MTU;
			break;
		case T_MOD:
			fp.fp_flags |= PF_OSFP_WSIZE_MOD;
			break;
		}
		fp.fp_wsize = window;

		switch (p_mod) {
		case T_DC:
			fp.fp_flags |= PF_OSFP_PSIZE_DC;
			break;
		case T_MOD:
			fp.fp_flags |= PF_OSFP_PSIZE_MOD;
		}
		fp.fp_psize = psize;


		switch (wscale_mod) {
		case T_DC:
			fp.fp_flags |= PF_OSFP_WSCALE_DC;
			break;
		case T_MOD:
			fp.fp_flags |= PF_OSFP_WSCALE_MOD;
		}
		fp.fp_wscale = wscale;

		switch (mss_mod) {
		case T_DC:
			fp.fp_flags |= PF_OSFP_MSS_DC;
			break;
		case T_MOD:
			fp.fp_flags |= PF_OSFP_MSS_MOD;
			break;
		}
		fp.fp_mss = mss;

		fp.fp_tcpopts = packed_tcpopts;
		fp.fp_optcnt = optcnt;
		if (ts0)
			fp.fp_flags |= PF_OSFP_TS0;

		if (class[0] == '@')
			fp.fp_os.fp_enflags |= PF_OSFP_GENERIC;
		if (class[0] == '*')
			fp.fp_os.fp_enflags |= PF_OSFP_NODETAIL;

		if (class[0] == '@' || class[0] == '*')
			strlcpy(fp.fp_os.fp_class_nm, class + 1,
			    sizeof(fp.fp_os.fp_class_nm));
		else
			strlcpy(fp.fp_os.fp_class_nm, class,
			    sizeof(fp.fp_os.fp_class_nm));
		strlcpy(fp.fp_os.fp_version_nm, version,
		    sizeof(fp.fp_os.fp_version_nm));
		strlcpy(fp.fp_os.fp_subtype_nm, subtype,
		    sizeof(fp.fp_os.fp_subtype_nm));

		add_fingerprint(dev, opts, &fp);

		fp.fp_flags |= (PF_OSFP_DF | PF_OSFP_INET6);
		fp.fp_psize += sizeof(struct ip6_hdr) - sizeof(struct ip);
		add_fingerprint(dev, opts, &fp);
	}

	if (class)
		free(class);
	if (version)
		free(version);
	if (subtype)
		free(subtype);
	if (desc)
		free(desc);
	if (tcpopts)
		free(tcpopts);

	fclose(in);

	if (opts & PF_OPT_VERBOSE2)
		printf("Loaded %d passive OS fingerprints\n",
		    fingerprint_count);
	return (0);
}