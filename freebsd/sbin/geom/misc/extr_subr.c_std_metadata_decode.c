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
struct std_metadata {int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32dec (unsigned char const*) ; 

__attribute__((used)) static void
std_metadata_decode(const unsigned char *data, struct std_metadata *md)
{

        bcopy(data, md->md_magic, sizeof(md->md_magic));
        md->md_version = le32dec(data + 16);
}