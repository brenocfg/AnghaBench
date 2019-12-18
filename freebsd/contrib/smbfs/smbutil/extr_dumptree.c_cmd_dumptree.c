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
struct smb_vc_info {int dummy; } ;
struct smb_share_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int SMB_INFO_NONE ; 
#define  SMB_INFO_SHARE 129 
#define  SMB_INFO_VC 128 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ loadsmbvfs () ; 
 int /*<<< orphan*/  print_shareinfo (void*) ; 
 int /*<<< orphan*/  print_vcinfo (void*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* smb_dumptree () ; 

int
cmd_dumptree(int argc, char *argv[])
{
	void *p, *op;
	int *itype;

	printf("SMB connections:\n");
#ifdef APPLE
	if (loadsmbvfs())
		errx(EX_OSERR, "SMB filesystem is not available");
#endif
	p = smb_dumptree();
	if (p == NULL) {
		printf("None\n");
		return 0;
	}
	op = p;
	for (;;) {
		itype = p;
		if (*itype == SMB_INFO_NONE)
			break;
		switch (*itype) {
		    case SMB_INFO_VC:
			print_vcinfo(p);
			p = (struct smb_vc_info*)p + 1;
			break;
		    case SMB_INFO_SHARE:
			print_shareinfo(p);
			p = (struct smb_share_info*)p + 1;
			break;
		    default:
			printf("Out of sync\n");
			free(op);
			return 1;
		    
		}
	}
	free(op);
	printf("\n");
	return 0;
}