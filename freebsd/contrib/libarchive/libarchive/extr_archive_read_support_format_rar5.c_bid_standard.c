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
typedef  int /*<<< orphan*/  uint8_t ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rar5_signature ; 
 int /*<<< orphan*/  rar5_signature_size ; 
 int /*<<< orphan*/  read_ahead (struct archive_read*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int bid_standard(struct archive_read* a) {
	const uint8_t* p;

	if(!read_ahead(a, rar5_signature_size, &p))
		return -1;

	if(!memcmp(rar5_signature, p, rar5_signature_size))
		return 30;

	return -1;
}