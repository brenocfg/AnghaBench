#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  force_overwrite; int /*<<< orphan*/  current_input_path; } ;
typedef  TYPE_1__ Context ;
typedef  int /*<<< orphan*/  BrotliDecoderState ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_FALSE ; 
 scalar_t__ BROTLI_TRUE ; 
 int /*<<< orphan*/ * BrotliDecoderCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliDecoderDestroyInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseFiles (TYPE_1__*,scalar_t__) ; 
 scalar_t__ DecompressFile (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NextFile (TYPE_1__*) ; 
 scalar_t__ OpenFiles (TYPE_1__*) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BROTLI_BOOL DecompressFiles(Context* context) {
  while (NextFile(context)) {
    BROTLI_BOOL is_ok = BROTLI_TRUE;
    BrotliDecoderState* s = BrotliDecoderCreateInstance(NULL, NULL, NULL);
    if (!s) {
      fprintf(stderr, "out of memory\n");
      return BROTLI_FALSE;
    }
    is_ok = OpenFiles(context);
    if (is_ok && !context->current_input_path &&
        !context->force_overwrite && isatty(STDIN_FILENO)) {
      fprintf(stderr, "Use -h help. Use -f to force input from a terminal.\n");
      is_ok = BROTLI_FALSE;
    }
    if (is_ok) is_ok = DecompressFile(context, s);
    BrotliDecoderDestroyInstance(s);
    if (!CloseFiles(context, is_ok)) is_ok = BROTLI_FALSE;
    if (!is_ok) return BROTLI_FALSE;
  }
  return BROTLI_TRUE;
}