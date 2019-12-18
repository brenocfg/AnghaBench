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
struct g_llvm_segment {int sg_start; int sg_count; int sg_end; int /*<<< orphan*/  sg_pvstart; int /*<<< orphan*/  sg_pvname; } ;
struct g_llvm_lv {int lv_extentcount; int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  lv_numsegs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GRAB_INT (char*,char*,char*,int) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_llvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GLLVM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SPLIT (char*,char*,char*) ; 
 int /*<<< orphan*/  free (struct g_llvm_segment*,int /*<<< orphan*/ ) ; 
 struct g_llvm_segment* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_next ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int
llvm_textconf_decode_sg(char **buf, char *tok, struct g_llvm_lv *lv)
{
	struct g_llvm_segment *sg;
	char *v;
	int count = 0;

	if (*buf == NULL || **buf == '\0')
		return (EINVAL);

	sg = malloc(sizeof(*sg), M_GLLVM, M_NOWAIT|M_ZERO);
	if (sg == NULL)
		return (ENOMEM);

	while ((tok = strsep(buf, "\n")) != NULL) {
		/* only a single linear stripe is supported */
		if (strstr(tok, "stripe_count")) {
			SPLIT(v, tok, "=");
			GRAB_INT("stripe_count", v, tok, count);
			if (count != 1)
				goto bad;
		}

		if (strstr(tok, "{"))
			goto bad;

		if (strstr(tok, "}"))
			break;

		if (strcmp(tok, "stripes = [") == 0) {
			tok = strsep(buf, "\n");
			if (tok == NULL)
				goto bad;

			strsep(&tok, "\"");
			if (tok == NULL)
				goto bad;	/* missing open quotes */
			v = strsep(&tok, "\"");
			if (tok == NULL)
				goto bad;	/* missing close quotes */
			strncpy(sg->sg_pvname, v, sizeof(sg->sg_pvname));
			if (*tok != ',')
				goto bad;	/* missing comma for stripe */
			tok++;

			sg->sg_pvstart = strtol(tok, &v, 10);
			if (v == tok)
				/* strtol did not eat any of the buffer */
				goto bad;

			continue;
		}

		/* parse 'key = value' lines */
		if (strstr(tok, "=")) {
			SPLIT(v, tok, "=");
			GRAB_INT("start_extent", v, tok, sg->sg_start);
			GRAB_INT("extent_count", v, tok, sg->sg_count);
			continue;
		}
	}
	if (tok == NULL)
		goto bad;
	/* basic checking */
	if (count != 1 || sg->sg_count == 0)
		goto bad;

	sg->sg_end = sg->sg_start + sg->sg_count - 1;
	lv->lv_numsegs++;
	lv->lv_extentcount += sg->sg_count;
	LIST_INSERT_HEAD(&lv->lv_segs, sg, sg_next);

	return (0);
bad:
	free(sg, M_GLLVM);
	return (-1);
}