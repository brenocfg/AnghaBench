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
typedef  int EFI_STATUS ;

/* Variables and functions */
 int EACCES ; 
 int EDOOFUS ; 
#define  EFI_ACCESS_DENIED 139 
#define  EFI_BUFFER_TOO_SMALL 138 
#define  EFI_DEVICE_ERROR 137 
#define  EFI_INVALID_PARAMETER 136 
#define  EFI_MEDIA_CHANGED 135 
#define  EFI_NOT_FOUND 134 
#define  EFI_NO_MEDIA 133 
#define  EFI_OUT_OF_RESOURCES 132 
#define  EFI_UNSUPPORTED 131 
#define  EFI_VOLUME_CORRUPTED 130 
#define  EFI_VOLUME_FULL 129 
#define  EFI_WRITE_PROTECTED 128 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int EOVERFLOW ; 
 int EPERM ; 
 int ESTALE ; 

int
efi_status_to_errno(EFI_STATUS status)
{
	int errno;

	switch (status) {
	case EFI_ACCESS_DENIED:
		errno = EPERM;
		break;

	case EFI_BUFFER_TOO_SMALL:
		errno = EOVERFLOW;
		break;

	case EFI_DEVICE_ERROR:
	case EFI_VOLUME_CORRUPTED:
		errno = EIO;
		break;

	case EFI_INVALID_PARAMETER:
		errno = EINVAL;
		break;

	case EFI_MEDIA_CHANGED:
		errno = ESTALE;
		break;

	case EFI_NO_MEDIA:
		errno = ENXIO;
		break;

	case EFI_NOT_FOUND:
		errno = ENOENT;
		break;

	case EFI_OUT_OF_RESOURCES:
		errno = ENOMEM;
		break;

	case EFI_UNSUPPORTED:
		errno = ENODEV;
		break;

	case EFI_VOLUME_FULL:
		errno = ENOSPC;
		break;

	case EFI_WRITE_PROTECTED:
		errno = EACCES;
		break;

	case 0:
		errno = 0;
		break;

	default:
		errno = EDOOFUS;
		break;
	}

	return (errno);
}