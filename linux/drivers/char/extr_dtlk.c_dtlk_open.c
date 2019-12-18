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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
#define  DTLK_MINOR 128 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  TRACE_TEXT (char*) ; 
 int /*<<< orphan*/  dtlk_busy ; 
 int iminor (struct inode*) ; 
 int stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int dtlk_open(struct inode *inode, struct file *file)
{
	TRACE_TEXT("(dtlk_open");

	switch (iminor(inode)) {
	case DTLK_MINOR:
		if (dtlk_busy)
			return -EBUSY;
		return stream_open(inode, file);

	default:
		return -ENXIO;
	}
}