#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ifreq {int /*<<< orphan*/  ifr_name; void* ifr_data; } ;
struct adapter {int /*<<< orphan*/  socket; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ifr ;
typedef  void* caddr_t ;
struct TYPE_9__ {int KeyLength; int /*<<< orphan*/  KeyMaterial; int /*<<< orphan*/  BSSID; int /*<<< orphan*/  KeyIndex; int /*<<< orphan*/  KeyRSC; } ;
struct TYPE_8__ {int Length; int KeyLength; char* BSSID; int /*<<< orphan*/  KeyIndex; int /*<<< orphan*/  KeyRSC; } ;
struct TYPE_7__ {scalar_t__ Oid; int Length; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ PACKET_OID_DATA ;
typedef  int /*<<< orphan*/  NDIS_802_11_MAC_ADDRESS ;
typedef  TYPE_2__ NDIS_802_11_KEY_COMPAT ;
typedef  TYPE_3__ NDIS_802_11_KEY ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ OID_802_11_ADD_KEY ; 
 int /*<<< orphan*/  SIOCGDRVSPEC ; 
 int /*<<< orphan*/  SIOCSDRVSPEC ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
PacketRequest(void *iface, BOOLEAN set, PACKET_OID_DATA *oid)
{
	struct adapter		*a;
	uint32_t		retval;
	struct ifreq		ifr;
	NDIS_802_11_KEY		*old;
	NDIS_802_11_KEY_COMPAT	*new;
	PACKET_OID_DATA		*o = NULL;

	if (iface == NULL)
		return(-1);

	a = iface;
	bzero((char *)&ifr, sizeof(ifr));

	/*
	 * This hack is necessary to work around a difference
	 * betwee the GNU C and Microsoft C compilers. The NDIS_802_11_KEY
	 * structure has a uint64_t in it, right after an array of
	 * chars. The Microsoft compiler inserts padding right before
	 * the 64-bit value to align it on a 64-bit boundary, but
	 * GCC only aligns it on a 32-bit boundary. Trying to pass
	 * the GCC-formatted structure to an NDIS binary driver
	 * fails because some of the fields appear to be at the
	 * wrong offsets.
	 *
	 * To get around this, if we detect someone is trying to do
	 * a set operation on OID_802_11_ADD_KEY, we shuffle the data
	 * into a properly padded structure and pass that into the
	 * driver instead. This allows the driver_ndis.c code supplied
	 * with wpa_supplicant to work unmodified.
	 */

	if (set == TRUE && oid->Oid == OID_802_11_ADD_KEY) {
		old = (NDIS_802_11_KEY *)&oid->Data;
		o = malloc(sizeof(PACKET_OID_DATA) +
		    sizeof(NDIS_802_11_KEY_COMPAT) + old->KeyLength);
		if (o == NULL)
			return(0);
		bzero((char *)o, sizeof(PACKET_OID_DATA) +
		    sizeof(NDIS_802_11_KEY_COMPAT) + old->KeyLength);
		o->Oid = oid->Oid;
		o->Length = sizeof(NDIS_802_11_KEY_COMPAT) + old->KeyLength;
		new = (NDIS_802_11_KEY_COMPAT *)&o->Data;
		new->KeyRSC = old->KeyRSC;
		new->Length = o->Length;
		new->KeyIndex = old->KeyIndex;
		new->KeyLength = old->KeyLength;
		bcopy(old->BSSID, new->BSSID, sizeof(NDIS_802_11_MAC_ADDRESS));
		bcopy(old->KeyMaterial, (char *)new +
		    sizeof(NDIS_802_11_KEY_COMPAT), new->KeyLength);
        	ifr.ifr_data = (caddr_t)o;
	} else
        	ifr.ifr_data = (caddr_t)oid;

        strlcpy(ifr.ifr_name, a->name, sizeof(ifr.ifr_name));

	if (set == TRUE)
		retval = ioctl(a->socket, SIOCSDRVSPEC, &ifr);
	else
		retval = ioctl(a->socket, SIOCGDRVSPEC, &ifr);

	if (o != NULL)
		free(o);

	if (retval)
		return(0);

	return(1);
}