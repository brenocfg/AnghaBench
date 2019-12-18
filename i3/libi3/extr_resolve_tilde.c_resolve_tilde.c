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
struct TYPE_4__ {int gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int GLOB_NOMATCH ; 
 int /*<<< orphan*/  GLOB_TILDE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 char* scalloc (size_t,int) ; 
 char* sstrdup (char const*) ; 
 char* sstrndup (char const*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

char *resolve_tilde(const char *path) {
    static glob_t globbuf;
    char *head, *tail, *result;

    tail = strchr(path, '/');
    head = sstrndup(path, tail ? (size_t)(tail - path) : strlen(path));

    int res = glob(head, GLOB_TILDE, NULL, &globbuf);
    free(head);
    /* no match, or many wildcard matches are bad */
    if (res == GLOB_NOMATCH || globbuf.gl_pathc != 1)
        result = sstrdup(path);
    else if (res != 0) {
        err(EXIT_FAILURE, "glob() failed");
    } else {
        head = globbuf.gl_pathv[0];
        result = scalloc(strlen(head) + (tail ? strlen(tail) : 0) + 1, 1);
        strcpy(result, head);
        if (tail) {
            strcat(result, tail);
        }
    }
    globfree(&globbuf);

    return result;
}