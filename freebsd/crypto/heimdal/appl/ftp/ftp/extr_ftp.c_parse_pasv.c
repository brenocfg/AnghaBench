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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sscanf (char const*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int
parse_pasv (struct sockaddr_in *sin4, const char *str)
{
    int a0, a1, a2, a3, p0, p1;

    /*
     * What we've got at this point is a string of comma separated
     * one-byte unsigned integer values. The first four are the an IP
     * address. The fifth is the MSB of the port number, the sixth is the
     * LSB. From that we'll prepare a sockaddr_in.
     */

    if (sscanf (str, "%d,%d,%d,%d,%d,%d",
		&a0, &a1, &a2, &a3, &p0, &p1) != 6) {
	printf ("Passive mode address scan failure. "
		"Shouldn't happen!\n");
	return -1;
    }
    if (a0 < 0 || a0 > 255 ||
	a1 < 0 || a1 > 255 ||
	a2 < 0 || a2 > 255 ||
	a3 < 0 || a3 > 255 ||
	p0 < 0 || p0 > 255 ||
	p1 < 0 || p1 > 255) {
	printf ("Can't parse passive mode string.\n");
	return -1;
    }
    memset (sin4, 0, sizeof(*sin4));
    sin4->sin_family      = AF_INET;
    sin4->sin_addr.s_addr = htonl ((a0 << 24) | (a1 << 16) |
				  (a2 << 8) | a3);
    sin4->sin_port = htons ((p0 << 8) | p1);
    return 0;
}