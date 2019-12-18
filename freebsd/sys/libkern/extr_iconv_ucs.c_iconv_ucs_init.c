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
struct iconv_converter_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODING_UNICODE ; 
 int /*<<< orphan*/  ENCODING_UTF8 ; 
 int iconv_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iconv_ucs_init(struct iconv_converter_class *dcp)
{
	int error;

	error = iconv_add(ENCODING_UNICODE, ENCODING_UNICODE, ENCODING_UTF8);
	if (error)
		return (error);
	error = iconv_add(ENCODING_UNICODE, ENCODING_UTF8, ENCODING_UNICODE);
	if (error)
		return (error);
	return (0);
}