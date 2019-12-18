#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int fs_mtime; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int IFREG ; 
 int IREAD ; 
 int SF_IMMUTABLE ; 
 int SF_NOUNLINK ; 
 int SUJ_MIN ; 
 int /*<<< orphan*/  di_flags ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_modrev ; 
 int /*<<< orphan*/  di_nlink ; 
 int /*<<< orphan*/  di_size ; 
 TYPE_1__* fs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sujino ; 

__attribute__((used)) static int
suj_verifyino(union dinode *ip)
{

	if (DIP(ip, di_nlink) != 1) {
		printf("Invalid link count %d for journal inode %ju\n",
		    DIP(ip, di_nlink), (uintmax_t)sujino);
		return (-1);
	}

	if ((DIP(ip, di_flags) & (SF_IMMUTABLE | SF_NOUNLINK)) !=
	    (SF_IMMUTABLE | SF_NOUNLINK)) {
		printf("Invalid flags 0x%X for journal inode %ju\n",
		    DIP(ip, di_flags), (uintmax_t)sujino);
		return (-1);
	}

	if (DIP(ip, di_mode) != (IFREG | IREAD)) {
		printf("Invalid mode %o for journal inode %ju\n",
		    DIP(ip, di_mode), (uintmax_t)sujino);
		return (-1);
	}

	if (DIP(ip, di_size) < SUJ_MIN) {
		printf("Invalid size %jd for journal inode %ju\n",
		    DIP(ip, di_size), (uintmax_t)sujino);
		return (-1);
	}

	if (DIP(ip, di_modrev) != fs->fs_mtime) {
		printf("Journal timestamp does not match fs mount time\n");
		return (-1);
	}

	return (0);
}