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
struct ptunit_result {int dummy; } ;
struct pt_block_decoder {int dummy; } ;

/* Variables and functions */
 struct pt_block_decoder* pt_blk_alloc_decoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (struct pt_block_decoder*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result alloc_decoder_null(void)
{
	struct pt_block_decoder *decoder;

	decoder = pt_blk_alloc_decoder(NULL);
	ptu_null(decoder);

	return ptu_passed();
}