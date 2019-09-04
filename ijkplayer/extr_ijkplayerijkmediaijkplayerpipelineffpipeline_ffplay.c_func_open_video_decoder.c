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
typedef  int /*<<< orphan*/  IJKFF_Pipenode ;
typedef  int /*<<< orphan*/  IJKFF_Pipeline ;
typedef  int /*<<< orphan*/  FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/ * ffpipenode_create_video_decoder_from_ffplay (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IJKFF_Pipenode *func_open_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return ffpipenode_create_video_decoder_from_ffplay(ffp);
}