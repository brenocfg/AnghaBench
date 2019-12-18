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
struct bhnd_nvram_prop {int refs; int /*<<< orphan*/ * val; struct bhnd_nvram_prop* name; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 struct bhnd_nvram_prop* bhnd_nv_calloc (int,int) ; 
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvram_prop*) ; 
 struct bhnd_nvram_prop* bhnd_nv_strdup (char const*) ; 
 int /*<<< orphan*/ * bhnd_nvram_val_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

struct bhnd_nvram_prop *
bhnd_nvram_prop_new(const char *name, bhnd_nvram_val *val)
{
	struct bhnd_nvram_prop *prop;

	prop = bhnd_nv_calloc(1, sizeof(*prop));
	if (prop == NULL)
		return NULL;

	/* Implicit caller-owned reference */
	prop->refs = 1;

	if ((prop->name = bhnd_nv_strdup(name)) == NULL)
		goto failed;

	if ((prop->val = bhnd_nvram_val_copy(val)) == NULL)
		goto failed;

	return (prop);

failed:
	if (prop->name != NULL)
		bhnd_nv_free(prop->name);

	if (prop->val != NULL)
		bhnd_nvram_val_release(prop->val);

	bhnd_nv_free(prop);
	return (NULL);
}