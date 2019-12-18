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
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int XF_ENC_LOCALE ; 
 int XF_ENC_UTF8 ; 
 scalar_t__ XOF_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_UTF8 ; 
 scalar_t__ XO_STYLE_TEXT ; 
 scalar_t__ xo_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xo_needed_encoding (xo_handle_t *xop)
{
    if (XOF_ISSET(xop, XOF_UTF8)) /* Check the override flag */
	return XF_ENC_UTF8;

    if (xo_style(xop) == XO_STYLE_TEXT) /* Text means locale */
	return XF_ENC_LOCALE;

    return XF_ENC_UTF8;		/* Otherwise, we love UTF-8 */
}