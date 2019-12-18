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
typedef  int /*<<< orphan*/  imgType_t ;
typedef  int /*<<< orphan*/  imgFlags_t ;
typedef  int /*<<< orphan*/  image_t ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/ * R_CreateImage2Internal (char const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

image_t *R_CreateImage2( const char *name, byte *pic, int width, int height, GLenum picFormat, int numMips, imgType_t type, imgFlags_t flags, int internalFormat ) {
  return R_CreateImage2Internal( name, pic, width, height, picFormat, numMips, type, flags, internalFormat, qtrue );
}