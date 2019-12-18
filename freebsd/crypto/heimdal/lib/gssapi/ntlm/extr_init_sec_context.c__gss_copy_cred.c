#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ntlm_cred ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_1__ key; struct TYPE_9__* username; struct TYPE_9__* domain; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strdup (TYPE_2__*) ; 

__attribute__((used)) static int
_gss_copy_cred(ntlm_cred from, ntlm_cred *to)
{
    *to = calloc(1, sizeof(**to));
    if (*to == NULL)
	return ENOMEM;
    (*to)->username = strdup(from->username);
    if ((*to)->username == NULL) {
	free(*to);
	return ENOMEM;
    }
    (*to)->domain = strdup(from->domain);
    if ((*to)->domain == NULL) {
	free((*to)->username);
	free(*to);
	return ENOMEM;
    }
    (*to)->key.data = malloc(from->key.length);
    if ((*to)->key.data == NULL) {
	free((*to)->domain);
	free((*to)->username);
	free(*to);
	return ENOMEM;
    }
    memcpy((*to)->key.data, from->key.data, from->key.length);
    (*to)->key.length = from->key.length;

    return 0;
}