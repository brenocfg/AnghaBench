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
struct pt_config {int dummy; } ;
struct pt_block_decoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_block_decoder*) ; 
 struct pt_block_decoder* malloc (int) ; 
 int pt_blk_decoder_init (struct pt_block_decoder*,struct pt_config const*) ; 

struct pt_block_decoder *
pt_blk_alloc_decoder(const struct pt_config *config)
{
	struct pt_block_decoder *decoder;
	int errcode;

	decoder = malloc(sizeof(*decoder));
	if (!decoder)
		return NULL;

	errcode = pt_blk_decoder_init(decoder, config);
	if (errcode < 0) {
		free(decoder);
		return NULL;
	}

	return decoder;
}