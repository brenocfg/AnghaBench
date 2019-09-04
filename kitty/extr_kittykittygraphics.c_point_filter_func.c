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
typedef  int /*<<< orphan*/  ImageRef ;
typedef  int /*<<< orphan*/  Image ;
typedef  int /*<<< orphan*/  CellPixelSize ;

/* Variables and functions */
 scalar_t__ x_filter_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ y_filter_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
point_filter_func(ImageRef *ref, Image *img, const void *data, CellPixelSize cell) {
    return x_filter_func(ref, img, data, cell) && y_filter_func(ref, img, data, cell);
}