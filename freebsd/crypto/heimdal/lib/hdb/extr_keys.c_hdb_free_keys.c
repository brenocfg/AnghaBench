#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  key; struct TYPE_5__* salt; struct TYPE_5__* mkvno; } ;
typedef  TYPE_1__ Key ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_Salt (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
hdb_free_keys (krb5_context context, int len, Key *keys)
{
    int i;

    for (i = 0; i < len; i++) {
	free(keys[i].mkvno);
	keys[i].mkvno = NULL;
	if (keys[i].salt != NULL) {
	    free_Salt(keys[i].salt);
	    free(keys[i].salt);
	    keys[i].salt = NULL;
	}
	krb5_free_keyblock_contents(context, &keys[i].key);
    }
    free (keys);
}