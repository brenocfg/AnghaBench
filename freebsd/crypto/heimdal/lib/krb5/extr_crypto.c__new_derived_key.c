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
struct _krb5_key_data {int dummy; } ;
struct _krb5_key_usage {unsigned int usage; struct _krb5_key_data key; } ;
typedef  TYPE_1__* krb5_crypto ;
struct TYPE_3__ {int num_key_usage; struct _krb5_key_usage* key_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct _krb5_key_usage*,int /*<<< orphan*/ ,int) ; 
 struct _krb5_key_usage* realloc (struct _krb5_key_usage*,int) ; 

__attribute__((used)) static struct _krb5_key_data *
_new_derived_key(krb5_crypto crypto, unsigned usage)
{
    struct _krb5_key_usage *d = crypto->key_usage;
    d = realloc(d, (crypto->num_key_usage + 1) * sizeof(*d));
    if(d == NULL)
	return NULL;
    crypto->key_usage = d;
    d += crypto->num_key_usage++;
    memset(d, 0, sizeof(*d));
    d->usage = usage;
    return &d->key;
}