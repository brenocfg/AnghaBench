#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int reserved; int /*<<< orphan*/  build; void* minor; void* major; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__ host_version; } ;
typedef  TYPE_2__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  NTLM_ENABLE_HOSTVERSION ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

int ntlm_client_set_version(
	ntlm_client *ntlm,
	uint8_t major,
	uint8_t minor,
	uint16_t build)
{
	assert(ntlm);

	ntlm->host_version.major = major;
	ntlm->host_version.minor = minor;
	ntlm->host_version.build = build;
	ntlm->host_version.reserved = 0x0f000000;

	ntlm->flags |= NTLM_ENABLE_HOSTVERSION;

	return 0;
}