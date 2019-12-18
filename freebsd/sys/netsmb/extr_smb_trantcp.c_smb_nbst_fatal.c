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
struct smb_vc {int dummy; } ;

/* Variables and functions */
#define  ECONNABORTED 130 
#define  ENETRESET 129 
#define  ENOTCONN 128 

__attribute__((used)) static int
smb_nbst_fatal(struct smb_vc *vcp, int error)
{
	switch (error) {
	    case ENOTCONN:
	    case ENETRESET:
	    case ECONNABORTED:
		return 1;
	}
	return 0;
}