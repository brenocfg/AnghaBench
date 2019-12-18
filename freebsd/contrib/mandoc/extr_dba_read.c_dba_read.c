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
struct dbm_page {char* arch; char* file; char* name; char* sect; int /*<<< orphan*/  desc; } ;
struct dbm_macro {int /*<<< orphan*/  pp; int /*<<< orphan*/  value; } ;
struct dba_array {int dummy; } ;
struct dba {int /*<<< orphan*/  pages; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBP_ARCH ; 
 int /*<<< orphan*/  DBP_FILE ; 
 int /*<<< orphan*/  DBP_NAME ; 
 int /*<<< orphan*/  DBP_SECT ; 
 int MACRO_MAX ; 
 int /*<<< orphan*/  dba_macro_new (struct dba*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dba* dba_new (int) ; 
 int /*<<< orphan*/  dba_page_add (struct dba_array*,int /*<<< orphan*/ ,char const*) ; 
 struct dba_array* dba_page_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  dbm_close () ; 
 int dbm_macro_count (int) ; 
 struct dbm_macro* dbm_macro_get (int,int) ; 
 int dbm_open (char const*) ; 
 int dbm_page_count () ; 
 struct dbm_page* dbm_page_get (int) ; 
 char* strchr (char const*,char) ; 

struct dba *
dba_read(const char *fname)
{
	struct dba		*dba;
	struct dba_array	*page;
	struct dbm_page		*pdata;
	struct dbm_macro	*mdata;
	const char		*cp;
	int32_t			 im, ip, iv, npages;

	if (dbm_open(fname) == -1)
		return NULL;
	npages = dbm_page_count();
	dba = dba_new(npages < 128 ? 128 : npages);
	for (ip = 0; ip < npages; ip++) {
		pdata = dbm_page_get(ip);
		page = dba_page_new(dba->pages, pdata->arch,
		    pdata->desc, pdata->file + 1, *pdata->file);
		for (cp = pdata->name; *cp != '\0'; cp = strchr(cp, '\0') + 1)
			dba_page_add(page, DBP_NAME, cp);
		for (cp = pdata->sect; *cp != '\0'; cp = strchr(cp, '\0') + 1)
			dba_page_add(page, DBP_SECT, cp);
		if ((cp = pdata->arch) != NULL)
			while (*(cp = strchr(cp, '\0') + 1) != '\0')
				dba_page_add(page, DBP_ARCH, cp);
		cp = pdata->file;
		while (*(cp = strchr(cp, '\0') + 1) != '\0')
			dba_page_add(page, DBP_FILE, cp);
	}
	for (im = 0; im < MACRO_MAX; im++) {
		for (iv = 0; iv < dbm_macro_count(im); iv++) {
			mdata = dbm_macro_get(im, iv);
			dba_macro_new(dba, im, mdata->value, mdata->pp);
		}
	}
	dbm_close();
	return dba;
}