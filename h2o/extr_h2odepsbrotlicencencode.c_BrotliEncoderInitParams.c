#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  disable_literal_context_modeling; scalar_t__ size_hint; scalar_t__ lgblock; int /*<<< orphan*/  lgwin; int /*<<< orphan*/  quality; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ BrotliEncoderParams ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DEFAULT_MODE ; 
 int /*<<< orphan*/  BROTLI_DEFAULT_QUALITY ; 
 int /*<<< orphan*/  BROTLI_DEFAULT_WINDOW ; 
 int /*<<< orphan*/  BROTLI_FALSE ; 

__attribute__((used)) static void BrotliEncoderInitParams(BrotliEncoderParams* params) {
  params->mode = BROTLI_DEFAULT_MODE;
  params->quality = BROTLI_DEFAULT_QUALITY;
  params->lgwin = BROTLI_DEFAULT_WINDOW;
  params->lgblock = 0;
  params->size_hint = 0;
  params->disable_literal_context_modeling = BROTLI_FALSE;
}