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
struct hdb_method {char* prefix; } ;

/* Variables and functions */
 struct hdb_method const dbmetod ; 
 struct hdb_method* methods ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static const struct hdb_method *
find_method (const char *filename, const char **rest)
{
    const struct hdb_method *h;

    for (h = methods; h->prefix != NULL; ++h) {
	if (strncmp (filename, h->prefix, strlen(h->prefix)) == 0) {
	    *rest = filename + strlen(h->prefix);
	    return h;
	}
    }
#if defined(HAVE_DB1) || defined(HAVE_DB3) || defined(HAVE_NDBM)
    if (strncmp(filename, "/", 1) == 0
	|| strncmp(filename, "./", 2) == 0
	|| strncmp(filename, "../", 3) == 0)
    {
	*rest = filename;
	return &dbmetod;
    }
#endif

    return NULL;
}