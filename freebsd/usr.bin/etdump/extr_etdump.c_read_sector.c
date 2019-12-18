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
typedef  int daddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ISO_DEFAULT_BLOCK_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_sector(FILE *iso, daddr_t sector, char *buffer)
{

	if (fseek(iso, sector * ISO_DEFAULT_BLOCK_SIZE, SEEK_SET) != 0) {
		return (errno);
	}
	if (fread(buffer, ISO_DEFAULT_BLOCK_SIZE, 1, iso) != 1) {
		return (errno);
	}
	return (0);
}