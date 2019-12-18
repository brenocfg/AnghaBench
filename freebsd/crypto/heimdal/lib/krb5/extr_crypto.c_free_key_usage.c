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
struct _krb5_key_usage {int /*<<< orphan*/  key; } ;
struct _krb5_encryption_type {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_free_key_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct _krb5_encryption_type*) ; 

__attribute__((used)) static void
free_key_usage(krb5_context context, struct _krb5_key_usage *ku,
	       struct _krb5_encryption_type *et)
{
    _krb5_free_key_data(context, &ku->key, et);
}