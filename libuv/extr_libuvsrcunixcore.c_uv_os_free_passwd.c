#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * homedir; int /*<<< orphan*/ * shell; int /*<<< orphan*/ * username; } ;
typedef  TYPE_1__ uv_passwd_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 

void uv_os_free_passwd(uv_passwd_t* pwd) {
  if (pwd == NULL)
    return;

  /*
    The memory for name, shell, and homedir are allocated in a single
    uv__malloc() call. The base of the pointer is stored in pwd->username, so
    that is the field that needs to be freed.
  */
  uv__free(pwd->username);
  pwd->username = NULL;
  pwd->shell = NULL;
  pwd->homedir = NULL;
}