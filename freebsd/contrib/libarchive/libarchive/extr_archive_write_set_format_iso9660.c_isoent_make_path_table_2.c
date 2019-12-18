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
struct vdd {int vdd_type; struct path_table* pathtbl; } ;
struct path_table {int cnt; struct isoent** sorted; struct isoent* first; } ;
struct isoent {int /*<<< orphan*/  dir_number; struct isoent* ptnext; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
typedef  int /*<<< orphan*/  __compar_fn_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  VDD_ENHANCED 130 
#define  VDD_JOLIET 129 
#define  VDD_PRIMARY 128 
 int /*<<< orphan*/  _compare_path_table ; 
 int /*<<< orphan*/  _compare_path_table_joliet ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct isoent** malloc (int) ; 
 int /*<<< orphan*/  qsort (struct isoent**,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isoent_make_path_table_2(struct archive_write *a, struct vdd *vdd,
    int depth, int *dir_number)
{
	struct isoent *np;
	struct isoent **enttbl;
	struct path_table *pt;
	int i;

	pt = &vdd->pathtbl[depth];
	if (pt->cnt == 0) {
		pt->sorted = NULL;
		return (ARCHIVE_OK);
	}
	enttbl = malloc(pt->cnt * sizeof(struct isoent *));
	if (enttbl == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	pt->sorted = enttbl;
	for (np = pt->first; np != NULL; np = np->ptnext)
		*enttbl ++ = np;
	enttbl = pt->sorted;

	switch (vdd->vdd_type) {
	case VDD_PRIMARY:
	case VDD_ENHANCED:
#ifdef __COMPAR_FN_T
		qsort(enttbl, pt->cnt, sizeof(struct isoent *),
		    (__compar_fn_t)_compare_path_table);
#else
		qsort(enttbl, pt->cnt, sizeof(struct isoent *),
		    _compare_path_table);
#endif
		break;
	case VDD_JOLIET:
#ifdef __COMPAR_FN_T
		qsort(enttbl, pt->cnt, sizeof(struct isoent *),
		    (__compar_fn_t)_compare_path_table_joliet);
#else
		qsort(enttbl, pt->cnt, sizeof(struct isoent *),
		    _compare_path_table_joliet);
#endif
		break;
	}
	for (i = 0; i < pt->cnt; i++)
		enttbl[i]->dir_number = (*dir_number)++;

	return (ARCHIVE_OK);
}