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
typedef  int /*<<< orphan*/  fufh_type_t ;

/* Variables and functions */
 int FEXEC ; 
 int FREAD ; 
 int /*<<< orphan*/  FUFH_EXEC ; 
 int /*<<< orphan*/  FUFH_RDONLY ; 
 int /*<<< orphan*/  FUFH_RDWR ; 
 int /*<<< orphan*/  FUFH_WRONLY ; 
 int FWRITE ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static inline fufh_type_t
fflags_2_fufh_type(int fflags)
{
	if ((fflags & FREAD) && (fflags & FWRITE))
		return FUFH_RDWR;
	else if (fflags & (FWRITE))
		return FUFH_WRONLY;
	else if (fflags & (FREAD))
		return FUFH_RDONLY;
	else if (fflags & (FEXEC))
		return FUFH_EXEC;
	else
		panic("FUSE: What kind of a flag is this (%x)?", fflags);
}