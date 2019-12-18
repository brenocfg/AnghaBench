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
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
#define  EACCES 139 
 int /*<<< orphan*/  EFI_ACCESS_DENIED ; 
 int /*<<< orphan*/  EFI_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EFI_DEVICE_ERROR ; 
 int /*<<< orphan*/  EFI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EFI_MEDIA_CHANGED ; 
 int /*<<< orphan*/  EFI_NOT_FOUND ; 
 int /*<<< orphan*/  EFI_NO_MEDIA ; 
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 int /*<<< orphan*/  EFI_VOLUME_FULL ; 
 int /*<<< orphan*/  EFI_WRITE_PROTECTED ; 
#define  EINVAL 138 
#define  EIO 137 
#define  ENODEV 136 
#define  ENOENT 135 
#define  ENOMEM 134 
#define  ENOSPC 133 
#define  ENOTSUP 132 
#define  ENXIO 131 
#define  EOVERFLOW 130 
#define  EPERM 129 
#define  ESTALE 128 

EFI_STATUS
errno_to_efi_status(int errno)
{
        EFI_STATUS status;

        switch (errno) {
        case EPERM:
                status = EFI_ACCESS_DENIED;
                break;

        case EOVERFLOW:
                status = EFI_BUFFER_TOO_SMALL;
                break;

        case EIO:
                status = EFI_DEVICE_ERROR;
                break;

        case EINVAL:
                status = EFI_INVALID_PARAMETER;
                break;

        case ESTALE:
                status = EFI_MEDIA_CHANGED;
                break;

        case ENXIO:
                status = EFI_NO_MEDIA;
                break;

        case ENOENT:
                status = EFI_NOT_FOUND;
                break;

        case ENOMEM:
                status = EFI_OUT_OF_RESOURCES;
                break;

        case ENOTSUP:
        case ENODEV:
                status = EFI_UNSUPPORTED;
                break;

        case ENOSPC:
                status = EFI_VOLUME_FULL;
                break;

        case EACCES:
                status = EFI_WRITE_PROTECTED;
                break;

        case 0:
                status = EFI_SUCCESS;
                break;

        default:
                status = EFI_DEVICE_ERROR;
                break;
        }

        return (status);
}