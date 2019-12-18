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
struct fwimage_trailer {int size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWIMAGE_SIGNATURE ; 
 int /*<<< orphan*/  SIGNATURE_MAXLEN ; 
 scalar_t__ append_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fwimage_trailer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_trailer (int /*<<< orphan*/ ,struct fwimage_trailer*) ; 
 int /*<<< orphan*/  firmware_file ; 
 int /*<<< orphan*/  signature_file ; 

__attribute__((used)) static int
add_signature(struct fwimage_trailer *tr)
{
	if (!signature_file)
		return 0;

	tr->type = FWIMAGE_SIGNATURE;
	tr->size = sizeof(*tr);

	if (append_data(signature_file, firmware_file, tr, SIGNATURE_MAXLEN))
		return 1;

	append_trailer(firmware_file, tr);

	return 0;
}