#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fd_type {int sectrac; int secsize; int datalen; int gap; int tracks; int heads; int f_gap; int f_inter; int offset_side2; int size; int /*<<< orphan*/  flags; void* trans; } ;
typedef  enum fd_drivetype { ____Placeholder_fd_drivetype } fd_drivetype ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 void* FDC_1MBPS ; 
 void* FDC_250KBPS ; 
 void* FDC_300KBPS ; 
 void* FDC_500KBPS ; 
#define  FDT_12M 132 
#define  FDT_144M 131 
#define  FDT_288M 130 
#define  FDT_360K 129 
#define  FDT_720K 128 
 int /*<<< orphan*/  FL_2STEP ; 
 int /*<<< orphan*/  FL_AUTO ; 
 int /*<<< orphan*/  FL_MFM ; 
 int /*<<< orphan*/  FL_PERPND ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getnum (char*,int*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

void
parse_fmt(const char *s, enum fd_drivetype type,
	  struct fd_type in, struct fd_type *out)
{
	int i, j;
	const char *cp;
	char *s1;

	*out = in;

	for (i = 0;; i++) {
		if (s == NULL)
			break;

		if ((cp = strchr(s, ',')) == NULL) {
			s1 = strdup(s);
			if (s1 == NULL)
				abort();
			s = 0;
		} else {
			s1 = malloc(cp - s + 1);
			if (s1 == NULL)
				abort();
			memcpy(s1, s, cp - s);
			s1[cp - s] = 0;

			s = cp + 1;
		}
		if (strlen(s1) == 0) {
			free(s1);
			continue;
		}

		switch (i) {
		case 0:		/* sectrac */
			if (getnum(s1, &out->sectrac))
				errx(EX_USAGE,
				     "bad numeric value for sectrac: %s", s1);
			break;

		case 1:		/* secsize */
			if (getnum(s1, &j))
				errx(EX_USAGE,
				     "bad numeric value for secsize: %s", s1);
			if (j == 128) out->secsize = 0;
			else if (j == 256) out->secsize = 1;
			else if (j == 512) out->secsize = 2;
			else if (j == 1024) out->secsize = 3;
			else
				errx(EX_USAGE, "bad sector size %d", j);
			break;

		case 2:		/* datalen */
			if (getnum(s1, &j))
				errx(EX_USAGE,
				     "bad numeric value for datalen: %s", s1);
			if (j >= 256)
				errx(EX_USAGE, "bad datalen %d", j);
			out->datalen = j;
			break;

		case 3:		/* gap */
			if (getnum(s1, &out->gap))
				errx(EX_USAGE,
				     "bad numeric value for gap: %s", s1);
			break;

		case 4:		/* ncyls */
			if (getnum(s1, &j))
				errx(EX_USAGE,
				     "bad numeric value for ncyls: %s", s1);
			if (j > 85)
				errx(EX_USAGE, "bad # of cylinders %d", j);
			out->tracks = j;
			break;

		case 5:		/* speed */
			if (getnum(s1, &j))
				errx(EX_USAGE,
				     "bad numeric value for speed: %s", s1);
			switch (type) {
			default:
				abort(); /* paranoia */

			case FDT_360K:
			case FDT_720K:
				if (j == 250)
					out->trans = FDC_250KBPS;
				else
					errx(EX_USAGE, "bad speed %d", j);
				break;

			case FDT_12M:
				if (j == 300)
					out->trans = FDC_300KBPS;
				else if (j == 250)
					out->trans = FDC_250KBPS;
				else if (j == 500)
					out->trans = FDC_500KBPS;
				else
					errx(EX_USAGE, "bad speed %d", j);
				break;

			case FDT_288M:
				if (j == 1000)
					out->trans = FDC_1MBPS;
				/* FALLTHROUGH */
			case FDT_144M:
				if (j == 250)
					out->trans = FDC_250KBPS;
				else if (j == 500)
					out->trans = FDC_500KBPS;
				else
					errx(EX_USAGE, "bad speed %d", j);
				break;
			}
			break;

		case 6:		/* heads */
			if (getnum(s1, &j))
				errx(EX_USAGE,
				     "bad numeric value for heads: %s", s1);
			if (j == 1 || j == 2)
				out->heads = j;
			else
				errx(EX_USAGE, "bad # of heads %d", j);
			break;

		case 7:		/* f_gap */
			if (getnum(s1, &out->f_gap))
				errx(EX_USAGE,
				     "bad numeric value for f_gap: %s", s1);
			break;

		case 8:		/* f_inter */
			if (getnum(s1, &out->f_inter))
				errx(EX_USAGE,
				     "bad numeric value for f_inter: %s", s1);
			break;

		case 9:		/* offs2 */
			if (getnum(s1, &out->offset_side2))
				errx(EX_USAGE,
				     "bad numeric value for offs2: %s", s1);
			break;

		default:
			if (strcmp(s1, "+mfm") == 0)
				out->flags |= FL_MFM;
			else if (strcmp(s1, "-mfm") == 0)
				out->flags &= ~FL_MFM;
			else if (strcmp(s1, "+auto") == 0)
				out->flags |= FL_AUTO;
			else if (strcmp(s1, "-auto") == 0)
				out->flags &= ~FL_AUTO;
			else if (strcmp(s1, "+2step") == 0)
				out->flags |= FL_2STEP;
			else if (strcmp(s1, "-2step") == 0)
				out->flags &= ~FL_2STEP;
			else if (strcmp(s1, "+perpnd") == 0)
				out->flags |= FL_PERPND;
			else if (strcmp(s1, "-perpnd") == 0)
				out->flags &= ~FL_PERPND;
			else
				errx(EX_USAGE, "bad flag: %s", s1);
			break;
		}
		free(s1);
	}

	out->size = out->tracks * out->heads * out->sectrac;
}