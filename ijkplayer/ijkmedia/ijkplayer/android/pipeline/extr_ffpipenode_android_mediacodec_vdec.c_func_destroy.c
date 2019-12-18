#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/ * jsurface; int /*<<< orphan*/  codecpar; int /*<<< orphan*/ * bsfc; int /*<<< orphan*/  orig_extradata; int /*<<< orphan*/  output_aformat; int /*<<< orphan*/  input_aformat; int /*<<< orphan*/  acodec; int /*<<< orphan*/  acodec_first_dequeue_output_mutex; int /*<<< orphan*/  acodec_first_dequeue_output_cond; int /*<<< orphan*/  acodec_mutex; int /*<<< orphan*/  acodec_cond; int /*<<< orphan*/  any_input_mutex; int /*<<< orphan*/  any_input_cond; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ IJKFF_Pipenode_Opaque ;
typedef  TYPE_2__ IJKFF_Pipenode ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  SDL_AMediaCodec_decreaseReferenceP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_AMediaFormat_deleteP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyCondP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_DestroyMutexP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_JNI_DeleteGlobalRefP (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SDL_JNI_SetupThreadEnv (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_bitstream_filter_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_parameters_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void func_destroy(IJKFF_Pipenode *node)
{
    if (!node || !node->opaque)
        return;

    IJKFF_Pipenode_Opaque *opaque = node->opaque;

    SDL_DestroyCondP(&opaque->any_input_cond);
    SDL_DestroyMutexP(&opaque->any_input_mutex);
    SDL_DestroyCondP(&opaque->acodec_cond);
    SDL_DestroyMutexP(&opaque->acodec_mutex);
    SDL_DestroyCondP(&opaque->acodec_first_dequeue_output_cond);
    SDL_DestroyMutexP(&opaque->acodec_first_dequeue_output_mutex);

    SDL_AMediaCodec_decreaseReferenceP(&opaque->acodec);
    SDL_AMediaFormat_deleteP(&opaque->input_aformat);
    SDL_AMediaFormat_deleteP(&opaque->output_aformat);

#if AMC_USE_AVBITSTREAM_FILTER
    av_freep(&opaque->orig_extradata);

    if (opaque->bsfc) {
        av_bitstream_filter_close(opaque->bsfc);
        opaque->bsfc = NULL;
    }
#endif

    avcodec_parameters_free(&opaque->codecpar);

    JNIEnv *env = NULL;
    if (JNI_OK == SDL_JNI_SetupThreadEnv(&env)) {
        if (opaque->jsurface != NULL) {
            SDL_JNI_DeleteGlobalRefP(env, &opaque->jsurface);
        }
    }
}