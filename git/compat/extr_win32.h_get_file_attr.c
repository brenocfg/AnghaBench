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
typedef  int /*<<< orphan*/  WIN32_FILE_ATTRIBUTE_DATA ;

/* Variables and functions */
 int EACCES ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
#define  ERROR_ACCESS_DENIED 133 
#define  ERROR_BUFFER_OVERFLOW 132 
#define  ERROR_LOCK_VIOLATION 131 
#define  ERROR_NOT_ENOUGH_MEMORY 130 
#define  ERROR_SHARING_BUFFER_EXCEEDED 129 
#define  ERROR_SHARING_VIOLATION 128 
 scalar_t__ GetFileAttributesExA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileExInfoStandard ; 
 int GetLastError () ; 

__attribute__((used)) static inline int get_file_attr(const char *fname, WIN32_FILE_ATTRIBUTE_DATA *fdata)
{
	if (GetFileAttributesExA(fname, GetFileExInfoStandard, fdata))
		return 0;

	switch (GetLastError()) {
	case ERROR_ACCESS_DENIED:
	case ERROR_SHARING_VIOLATION:
	case ERROR_LOCK_VIOLATION:
	case ERROR_SHARING_BUFFER_EXCEEDED:
		return EACCES;
	case ERROR_BUFFER_OVERFLOW:
		return ENAMETOOLONG;
	case ERROR_NOT_ENOUGH_MEMORY:
		return ENOMEM;
	default:
		return ENOENT;
	}
}