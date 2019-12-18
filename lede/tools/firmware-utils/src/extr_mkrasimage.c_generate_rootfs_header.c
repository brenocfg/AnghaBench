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
struct file_info {int /*<<< orphan*/  size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ROOTFS_HEADER_LEN ; 
 size_t VERSION_STRING_LEN ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 unsigned int zyxel_chksm (unsigned char const*,int /*<<< orphan*/ ) ; 

char *generate_rootfs_header(struct file_info filesystem, char *version)
{
    size_t version_string_length;
    unsigned int chksm, size;
    char *rootfs_header;
    size_t ptr = 0;

    rootfs_header = malloc(ROOTFS_HEADER_LEN);
    if (!rootfs_header) {
        ERR("Couldn't allocate memory for rootfs header!");
        exit(EXIT_FAILURE);
    }

    /* Prepare padding for firmware-version string here */
    memset(rootfs_header, 0xff, ROOTFS_HEADER_LEN);

    chksm = zyxel_chksm((const unsigned char *)filesystem.data, filesystem.size);
    size = htonl(filesystem.size);

    /* 4 bytes:  checksum of the rootfs image */
    memcpy(rootfs_header + ptr, &chksm, 4);
    ptr += 4;

    /* 4 bytes:  length of the contained rootfs image file (big endian) */
    memcpy(rootfs_header + ptr, &size, 4);
    ptr += 4;

    /* 32 bytes:  Firmware Version string (NUL terminated, 0xff padded) */
    version_string_length = strlen(version) <= VERSION_STRING_LEN ? strlen(version) : VERSION_STRING_LEN;
    memcpy(rootfs_header + ptr, version, version_string_length);
    ptr += version_string_length;
    /* Add null-terminator */
    rootfs_header[ptr] = 0x0;

    return rootfs_header;
}