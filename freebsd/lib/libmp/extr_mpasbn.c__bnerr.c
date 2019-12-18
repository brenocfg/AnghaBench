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
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  ERR_reason_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPERRX (char*) ; 

__attribute__((used)) static void
_bnerr(const char *msg)
{

	ERR_load_crypto_strings();
	MPERRX(("%s: %s", msg, ERR_reason_error_string(ERR_get_error())));
}