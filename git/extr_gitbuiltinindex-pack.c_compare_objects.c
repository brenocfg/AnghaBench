#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct compare_data {unsigned long buf_size; TYPE_2__* entry; int /*<<< orphan*/  buf; int /*<<< orphan*/  st; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ read_istream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  xmalloc (unsigned long) ; 

__attribute__((used)) static int compare_objects(const unsigned char *buf, unsigned long size,
			   void *cb_data)
{
	struct compare_data *data = cb_data;

	if (data->buf_size < size) {
		free(data->buf);
		data->buf = xmalloc(size);
		data->buf_size = size;
	}

	while (size) {
		ssize_t len = read_istream(data->st, data->buf, size);
		if (len == 0)
			die(_("SHA1 COLLISION FOUND WITH %s !"),
			    oid_to_hex(&data->entry->idx.oid));
		if (len < 0)
			die(_("unable to read %s"),
			    oid_to_hex(&data->entry->idx.oid));
		if (memcmp(buf, data->buf, len))
			die(_("SHA1 COLLISION FOUND WITH %s !"),
			    oid_to_hex(&data->entry->idx.oid));
		size -= len;
		buf += len;
	}
	return 0;
}