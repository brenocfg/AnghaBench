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
typedef  scalar_t__ uint16_t ;
struct st_ptls_handshake_properties_t {int dummy; } ;
typedef  int /*<<< orphan*/  ptls_t ;

/* Variables and functions */
 scalar_t__ PICOTLS_VS_TEST_EXTENSION ; 

int collect_test_extension(ptls_t *tls, struct st_ptls_handshake_properties_t *properties, uint16_t type)
{
	return type == PICOTLS_VS_TEST_EXTENSION;
}