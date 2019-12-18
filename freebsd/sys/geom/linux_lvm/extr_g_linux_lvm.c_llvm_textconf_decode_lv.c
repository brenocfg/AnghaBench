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
struct g_llvm_vg {int /*<<< orphan*/  vg_lvs; } ;
struct g_llvm_segment {scalar_t__ lv_sgcount; scalar_t__ lv_numsegs; int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  lv_uuid; int /*<<< orphan*/  lv_name; void* lv_firstsg; struct g_llvm_vg* lv_vg; } ;
struct g_llvm_lv {scalar_t__ lv_sgcount; scalar_t__ lv_numsegs; int /*<<< orphan*/  lv_segs; int /*<<< orphan*/  lv_uuid; int /*<<< orphan*/  lv_name; void* lv_firstsg; struct g_llvm_vg* lv_vg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GRAB_INT (char*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  GRAB_STR (char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  G_LLVM_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_llvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_llvm_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GLLVM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SPLIT (char*,char*,char*) ; 
 int /*<<< orphan*/  free (struct g_llvm_segment*,int /*<<< orphan*/ ) ; 
 size_t llvm_grab_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  llvm_textconf_decode_sg (char**,char*,struct g_llvm_segment*) ; 
 int /*<<< orphan*/  lv_next ; 
 struct g_llvm_segment* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_next ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int
llvm_textconf_decode_lv(char **buf, char *tok, struct g_llvm_vg *vg)
{
	struct g_llvm_lv	*lv;
	struct g_llvm_segment *sg;
	char *v;
	size_t len;

	if (*buf == NULL || **buf == '\0')
		return (EINVAL);

	lv = malloc(sizeof(*lv), M_GLLVM, M_NOWAIT|M_ZERO);
	if (lv == NULL)
		return (ENOMEM);

	lv->lv_vg = vg;
	LIST_INIT(&lv->lv_segs);

	if (tok == NULL)
		goto bad;
	len = llvm_grab_name(lv->lv_name, tok);
	if (len == 0)
		goto bad;

	while ((tok = strsep(buf, "\n")) != NULL) {
		if (strstr(tok, "{")) {
			if (strstr(tok, "segment")) {
				llvm_textconf_decode_sg(buf, tok, lv);
				continue;
			} else
				/* unexpected section */
				goto bad;
		}

		if (strstr(tok, "}"))
			break;

		/* parse 'key = value' lines */
		if (strstr(tok, "=")) {
			SPLIT(v, tok, "=");
			GRAB_STR("id", v, tok, lv->lv_uuid, sizeof(lv->lv_uuid));
			GRAB_INT("segment_count", v, tok, lv->lv_sgcount);
			continue;
		}
	}
	if (tok == NULL)
		goto bad;
	if (lv->lv_sgcount == 0 || lv->lv_sgcount != lv->lv_numsegs)
		/* zero or incomplete segment list */
		goto bad;

	/* Optimize for only one segment on the pv */
	lv->lv_firstsg = LIST_FIRST(&lv->lv_segs);
	LIST_INSERT_HEAD(&vg->vg_lvs, lv, lv_next);
	G_LLVM_DEBUG(3, "lv: name=%s uuid=%s", lv->lv_name, lv->lv_uuid);

	return (0);
bad:
	while ((sg = LIST_FIRST(&lv->lv_segs)) != NULL) {
		LIST_REMOVE(sg, sg_next);
		free(sg, M_GLLVM);
	}
	free(lv, M_GLLVM);
	return (-1);
}