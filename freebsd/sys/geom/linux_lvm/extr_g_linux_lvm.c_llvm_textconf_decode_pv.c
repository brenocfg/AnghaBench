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
struct g_llvm_vg {int /*<<< orphan*/  vg_pvs; } ;
struct g_llvm_pv {scalar_t__ pv_start; scalar_t__ pv_count; int /*<<< orphan*/  pv_uuid; int /*<<< orphan*/  pv_name; struct g_llvm_vg* pv_vg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GRAB_INT (char*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  GRAB_STR (char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  G_LLVM_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_llvm_pv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GLLVM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SPLIT (char*,char*,char*) ; 
 int /*<<< orphan*/  free (struct g_llvm_pv*,int /*<<< orphan*/ ) ; 
 size_t llvm_grab_name (int /*<<< orphan*/ ,char*) ; 
 struct g_llvm_pv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pv_next ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int
llvm_textconf_decode_pv(char **buf, char *tok, struct g_llvm_vg *vg)
{
	struct g_llvm_pv	*pv;
	char *v;
	size_t len;

	if (*buf == NULL || **buf == '\0')
		return (EINVAL);

	pv = malloc(sizeof(*pv), M_GLLVM, M_NOWAIT|M_ZERO);
	if (pv == NULL)
		return (ENOMEM);

	pv->pv_vg = vg;
	len = 0;
	if (tok == NULL)
		goto bad;
	len = llvm_grab_name(pv->pv_name, tok);
	if (len == 0)
		goto bad;

	while ((tok = strsep(buf, "\n")) != NULL) {
		if (strstr(tok, "{"))
			goto bad;

		if (strstr(tok, "}"))
			break;

		/* parse 'key = value' lines */
		if (strstr(tok, "=")) {
			SPLIT(v, tok, "=");
			GRAB_STR("id", v, tok, pv->pv_uuid, sizeof(pv->pv_uuid));
			GRAB_INT("pe_start", v, tok, pv->pv_start);
			GRAB_INT("pe_count", v, tok, pv->pv_count);
			continue;
		}
	}
	if (tok == NULL)
		goto bad;
	/* basic checking */
	if (pv->pv_count == 0)
		goto bad;

	LIST_INSERT_HEAD(&vg->vg_pvs, pv, pv_next);
	G_LLVM_DEBUG(3, "pv: name=%s uuid=%s", pv->pv_name, pv->pv_uuid);

	return (0);
bad:
	free(pv, M_GLLVM);
	return (-1);
}