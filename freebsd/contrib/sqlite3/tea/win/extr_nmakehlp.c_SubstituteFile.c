#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szCopy ;
struct TYPE_4__ {char* key; char* value; struct TYPE_4__* nextPtr; } ;
typedef  TYPE_1__ list_item_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  list_free (TYPE_1__**) ; 
 int /*<<< orphan*/  list_insert (TYPE_1__**,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int
SubstituteFile(
    const char *substitutions,
    const char *filename)
{
    size_t cbBuffer = 1024;
    static char szBuffer[1024], szCopy[1024];
    char *szResult = NULL;
    list_item_t *substPtr = NULL;
    FILE *fp, *sp;

    fp = fopen(filename, "rt");
    if (fp != NULL) {

	/*
	 * Build a list of substutitions from the first filename
	 */

	sp = fopen(substitutions, "rt");
	if (sp != NULL) {
	    while (fgets(szBuffer, cbBuffer, sp) != NULL) {
		unsigned char *ks, *ke, *vs, *ve;
		ks = (unsigned char*)szBuffer;
		while (ks && *ks && isspace(*ks)) ++ks;
		ke = ks;
		while (ke && *ke && !isspace(*ke)) ++ke;
		vs = ke;
		while (vs && *vs && isspace(*vs)) ++vs;
		ve = vs;
		while (ve && *ve && !(*ve == '\r' || *ve == '\n')) ++ve;
		*ke = 0, *ve = 0;
		list_insert(&substPtr, (char*)ks, (char*)vs);
	    }
	    fclose(sp);
	}

	/* debug: dump the list */
#ifdef _DEBUG
	{
	    int n = 0;
	    list_item_t *p = NULL;
	    for (p = substPtr; p != NULL; p = p->nextPtr, ++n) {
		fprintf(stderr, "% 3d '%s' => '%s'\n", n, p->key, p->value);
	    }
	}
#endif
	
	/*
	 * Run the substitutions over each line of the input
	 */
	
	while (fgets(szBuffer, cbBuffer, fp) != NULL) {
	    list_item_t *p = NULL;
	    for (p = substPtr; p != NULL; p = p->nextPtr) {
		char *m = strstr(szBuffer, p->key);
		if (m) {
		    char *cp, *op, *sp;
		    cp = szCopy;
		    op = szBuffer;
		    while (op != m) *cp++ = *op++;
		    sp = p->value;
		    while (sp && *sp) *cp++ = *sp++;
		    op += strlen(p->key);
		    while (*op) *cp++ = *op++;
		    *cp = 0;
		    memcpy(szBuffer, szCopy, sizeof(szCopy));
		}
	    }
	    printf(szBuffer);
	}
	
	list_free(&substPtr);
    }
    fclose(fp);
    return 0;
}