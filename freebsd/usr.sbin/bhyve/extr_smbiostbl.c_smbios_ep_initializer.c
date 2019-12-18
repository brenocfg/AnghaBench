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
typedef  int /*<<< orphan*/  uint32_t ;
struct smbios_entry_point {int eplen; int major; int minor; int bcdrev; int /*<<< orphan*/  staddr; int /*<<< orphan*/  ianchor; scalar_t__ revision; int /*<<< orphan*/  eanchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBIOS_ENTRY_EANCHOR ; 
 int /*<<< orphan*/  SMBIOS_ENTRY_EANCHORLEN ; 
 int /*<<< orphan*/  SMBIOS_ENTRY_IANCHOR ; 
 int /*<<< orphan*/  SMBIOS_ENTRY_IANCHORLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smbios_entry_point*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smbios_ep_initializer(struct smbios_entry_point *smbios_ep, uint32_t staddr)
{
	memset(smbios_ep, 0, sizeof(*smbios_ep));
	memcpy(smbios_ep->eanchor, SMBIOS_ENTRY_EANCHOR,
	    SMBIOS_ENTRY_EANCHORLEN);
	smbios_ep->eplen = 0x1F;
	assert(sizeof (struct smbios_entry_point) == smbios_ep->eplen);
	smbios_ep->major = 2;
	smbios_ep->minor = 6;
	smbios_ep->revision = 0;
	memcpy(smbios_ep->ianchor, SMBIOS_ENTRY_IANCHOR,
	    SMBIOS_ENTRY_IANCHORLEN);
	smbios_ep->staddr = staddr;
	smbios_ep->bcdrev = 0x24;
}