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
 int /*<<< orphan*/  BOARD_HEADER_LEN ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned int generate_board_header_checksum (char*,char*,char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

char *generate_board_header(char *kernel_hdr, char *rootfs_hdr, char *boardname)
{
    unsigned int board_checksum;
    char *board_hdr;

    board_hdr = malloc(BOARD_HEADER_LEN);
    if (!board_hdr) {
        ERR("Couldn't allocate memory for board header!");
        exit(EXIT_FAILURE);
    }
    memset(board_hdr, 0xff, BOARD_HEADER_LEN);

    /* 4 bytes:  checksum over the header partition (big endian) */
    board_checksum = generate_board_header_checksum(kernel_hdr, rootfs_hdr, boardname);
    memcpy(board_hdr, &board_checksum, 4);

    /* 32 bytes:  Model (e.g. "NBG6617", NUL termiated, 0xff padded) */
    memcpy(board_hdr + 4, boardname, strlen(boardname));
    board_hdr[4 + strlen(boardname)] = 0x0;

    return board_hdr;
}