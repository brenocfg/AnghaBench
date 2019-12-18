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

/* Variables and functions */
 int /*<<< orphan*/  public_key_free (void*) ; 
 int /*<<< orphan*/  public_key_signature_free (void*) ; 

__attribute__((used)) static void public_key_destroy(void *payload0, void *payload3)
{
	public_key_free(payload0);
	public_key_signature_free(payload3);
}