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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  kadm5_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERSION2 ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
proc_init(kadm5_server_context *contextp,
	  krb5_storage *in,
	  krb5_storage *out)
{
    CHECK(krb5_store_uint32(out, VERSION2)); /* api version */
    CHECK(krb5_store_uint32(out, 0)); /* code */
    CHECK(krb5_store_uint32(out, 0)); /* code */
}