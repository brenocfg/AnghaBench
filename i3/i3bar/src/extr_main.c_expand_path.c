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
struct TYPE_4__ {scalar_t__ gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int GLOB_NOCHECK ; 
 int GLOB_TILDE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 char* sstrdup (char*) ; 

__attribute__((used)) static char *expand_path(char *path) {
    static glob_t globbuf;
    if (glob(path, GLOB_NOCHECK | GLOB_TILDE, NULL, &globbuf) < 0) {
        ELOG("glob() failed\n");
        exit(EXIT_FAILURE);
    }
    char *result = sstrdup(globbuf.gl_pathc > 0 ? globbuf.gl_pathv[0] : path);
    globfree(&globbuf);
    return result;
}