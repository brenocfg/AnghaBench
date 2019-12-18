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
struct uio {int uio_resid; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  evtchn ;

/* Variables and functions */
 int EINVAL ; 
 int XSD_READ_SIZE ; 
 int snprintf (char*,int,char*,int) ; 
 int uiomove (char*,int,struct uio*) ; 
 int xs_evtchn () ; 

__attribute__((used)) static int
xsd_dev_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	char evtchn[XSD_READ_SIZE];
	int error, len;

	len = snprintf(evtchn, sizeof(evtchn), "%u", xs_evtchn());
	if (len < 0 || len > uio->uio_resid)
		return (EINVAL);

	error = uiomove(evtchn, len, uio);
	if (error)
		return (error);

	return (0);
}