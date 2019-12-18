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
struct isoent {int dummy; } ;
struct idrent {int /*<<< orphan*/  isoent; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int isoent_cmp_iso9660_identifier (struct isoent const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isoent_cmp_key_iso9660(const struct archive_rb_node *node, const void *key)
{
	const struct isoent *isoent = (const struct isoent *)key;
	const struct idrent *idrent = (const struct idrent *)node;

	return (isoent_cmp_iso9660_identifier(isoent, idrent->isoent));
}