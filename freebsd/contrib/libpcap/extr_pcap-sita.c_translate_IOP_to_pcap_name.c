#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* iface; } ;
typedef  TYPE_1__ unit_t ;
struct TYPE_7__ {int iftype; char* IOPname; char* name; struct TYPE_7__* next; } ;
typedef  TYPE_2__ iface_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
#define  DLT_EN10MB 129 
#define  DLT_SITA 128 
 int atoi (char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nonUnified_IOP_port_name (char*,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unified_IOP_port_name (char*,int,char*,TYPE_1__*,int) ; 

__attribute__((used)) static char *translate_IOP_to_pcap_name(unit_t *u, char *IOPname, bpf_u_int32 iftype) {
	iface_t		*iface_ptr, *iface;
	char		*name;
	char		buf[32];
	char		*proto;
	char		*port;
	int			IOPportnum = 0;

	iface = malloc(sizeof(iface_t));		/* get memory for a structure */
	if (iface == NULL) {	/* oops, we didn't get the memory requested	*/
		fprintf(stderr, "Error...couldn't allocate memory for interface structure...value of errno is: %d\n", errno);
		return NULL;
	}
	memset((char *)iface, 0, sizeof(iface_t));	/* bzero is deprecated(), replaced with memset() */

	iface->iftype = iftype;					/* remember the interface type of this interface */

	name = malloc(strlen(IOPname) + 1);		/* get memory for the IOP's name */
        if (name == NULL) {    /* oops, we didn't get the memory requested     */
                fprintf(stderr, "Error...couldn't allocate memory for IOPname...value of errno is: %d\n", errno);
                return NULL;
        }

	strcpy(name, IOPname);					/* and copy it in */
	iface->IOPname = name;					/* and stick it into the structure */

	if (strncmp(IOPname, "lo", 2) == 0) {
		IOPportnum = atoi(&IOPname[2]);
		switch (iftype) {
			case DLT_EN10MB:
				nonUnified_IOP_port_name(buf, sizeof buf, "lo", u);
				break;
			default:
				unified_IOP_port_name(buf, sizeof buf, "???", u, IOPportnum);
				break;
		}
	} else if (strncmp(IOPname, "eth", 3) == 0) {
		IOPportnum = atoi(&IOPname[3]);
		switch (iftype) {
			case DLT_EN10MB:
				nonUnified_IOP_port_name(buf, sizeof buf, "eth", u);
				break;
			default:
				unified_IOP_port_name(buf, sizeof buf, "???", u, IOPportnum);
				break;
		}
	} else if (strncmp(IOPname, "wan", 3) == 0) {
		IOPportnum = atoi(&IOPname[3]);
		switch (iftype) {
			case DLT_SITA:
				unified_IOP_port_name(buf, sizeof buf, "wan", u, IOPportnum);
				break;
			default:
				unified_IOP_port_name(buf, sizeof buf, "???", u, IOPportnum);
				break;
		}
	} else {
		fprintf(stderr, "Error... invalid IOP name %s\n", IOPname);
		return NULL;
	}

	name = malloc(strlen(buf) + 1);			/* get memory for that name */
        if (name == NULL) {    /* oops, we didn't get the memory requested     */
                fprintf(stderr, "Error...couldn't allocate memory for IOP port name...value of errno is: %d\n", errno);
                return NULL;
        }

	strcpy(name, buf);						/* and copy it in */
	iface->name = name;						/* and stick it into the structure */

	if (u->iface == 0) {					/* if this is the first name */
		u->iface = iface;					/* stick this entry at the head of the list */
	} else {
		iface_ptr = u->iface;
		while (iface_ptr->next) {			/* othewise scan the list */
			iface_ptr = iface_ptr->next;	/* till we're at the last entry */
		}
		iface_ptr->next = iface;			/* then tack this entry on the end of the list */
	}
	return iface->name;
}