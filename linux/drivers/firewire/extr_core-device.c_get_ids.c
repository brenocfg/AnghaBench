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
typedef  int /*<<< orphan*/  u32 ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
#define  CSR_MODEL 131 
#define  CSR_SPECIFIER_ID 130 
#define  CSR_VENDOR 129 
#define  CSR_VERSION 128 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/  const*) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 

__attribute__((used)) static void get_ids(const u32 *directory, int *id)
{
	struct fw_csr_iterator ci;
	int key, value;

	fw_csr_iterator_init(&ci, directory);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		switch (key) {
		case CSR_VENDOR:	id[0] = value; break;
		case CSR_MODEL:		id[1] = value; break;
		case CSR_SPECIFIER_ID:	id[2] = value; break;
		case CSR_VERSION:	id[3] = value; break;
		}
	}
}