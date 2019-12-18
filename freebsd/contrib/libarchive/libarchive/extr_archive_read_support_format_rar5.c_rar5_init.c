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
struct TYPE_2__ {int /*<<< orphan*/  filters; } ;
struct rar5 {TYPE_1__ cstate; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ CDE_OK ; 
 scalar_t__ cdeque_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct rar5*,int /*<<< orphan*/ ,int) ; 
 int* rar5_signature ; 
 size_t rar5_signature_size ; 

__attribute__((used)) static int rar5_init(struct rar5* rar) {
	ssize_t i;

	memset(rar, 0, sizeof(struct rar5));

	/* Decrypt the magic signature pattern. Check the comment near the
	 * `rar5_signature` symbol to read the rationale behind this. */

	if(rar5_signature[0] == 243) {
		for(i = 0; i < rar5_signature_size; i++) {
			rar5_signature[i] ^= 0xA1;
		}
	}

	if(CDE_OK != cdeque_init(&rar->cstate.filters, 8192))
		return ARCHIVE_FATAL;

	return ARCHIVE_OK;
}