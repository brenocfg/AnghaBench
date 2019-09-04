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
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_5__ {int /*<<< orphan*/  func_setBuffer; int /*<<< orphan*/  func_setInt32; int /*<<< orphan*/  func_getInt32; int /*<<< orphan*/  func_delete; TYPE_1__* opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/  android_media_format; } ;
typedef  TYPE_1__ SDL_AMediaFormat_Opaque ;
typedef  TYPE_2__ SDL_AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_AMediaFormatJava_delete ; 
 int /*<<< orphan*/  SDL_AMediaFormatJava_getInt32 ; 
 int /*<<< orphan*/  SDL_AMediaFormatJava_setBuffer ; 
 int /*<<< orphan*/  SDL_AMediaFormatJava_setInt32 ; 

__attribute__((used)) static void setup_aformat(SDL_AMediaFormat *aformat, jobject android_media_format) {
    SDL_AMediaFormat_Opaque *opaque = aformat->opaque;
    opaque->android_media_format = android_media_format;

    aformat->func_delete    = SDL_AMediaFormatJava_delete;
    aformat->func_getInt32  = SDL_AMediaFormatJava_getInt32;
    aformat->func_setInt32  = SDL_AMediaFormatJava_setInt32;
    aformat->func_setBuffer = SDL_AMediaFormatJava_setBuffer;
}