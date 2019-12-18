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
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  SDEI_DENIED 132 
#define  SDEI_INVALID_PARAMETERS 131 
#define  SDEI_NOT_SUPPORTED 130 
#define  SDEI_OUT_OF_RESOURCE 129 
#define  SDEI_PENDING 128 

__attribute__((used)) static int sdei_to_linux_errno(unsigned long sdei_err)
{
	switch (sdei_err) {
	case SDEI_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	case SDEI_INVALID_PARAMETERS:
		return -EINVAL;
	case SDEI_DENIED:
		return -EPERM;
	case SDEI_PENDING:
		return -EINPROGRESS;
	case SDEI_OUT_OF_RESOURCE:
		return -ENOMEM;
	}

	/* Not an error value ... */
	return sdei_err;
}