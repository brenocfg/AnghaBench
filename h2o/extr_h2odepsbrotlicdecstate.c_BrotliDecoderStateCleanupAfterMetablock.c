#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  htrees; } ;
struct TYPE_8__ {int /*<<< orphan*/  htrees; } ;
struct TYPE_7__ {int /*<<< orphan*/  htrees; } ;
struct TYPE_10__ {TYPE_3__ distance_hgroup; TYPE_2__ insert_copy_hgroup; TYPE_1__ literal_hgroup; int /*<<< orphan*/  dist_context_map; int /*<<< orphan*/  context_map; int /*<<< orphan*/  context_modes; } ;
typedef  TYPE_4__ BrotliDecoderState ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FREE (TYPE_4__*,int /*<<< orphan*/ ) ; 

void BrotliDecoderStateCleanupAfterMetablock(BrotliDecoderState* s) {
  BROTLI_FREE(s, s->context_modes);
  BROTLI_FREE(s, s->context_map);
  BROTLI_FREE(s, s->dist_context_map);
  BROTLI_FREE(s, s->literal_hgroup.htrees);
  BROTLI_FREE(s, s->insert_copy_hgroup.htrees);
  BROTLI_FREE(s, s->distance_hgroup.htrees);
}