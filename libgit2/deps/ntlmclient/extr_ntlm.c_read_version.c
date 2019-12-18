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
struct TYPE_3__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ ntlm_version ;
typedef  int /*<<< orphan*/  ntlm_client ;
typedef  int /*<<< orphan*/  ntlm_buf ;

/* Variables and functions */
 scalar_t__ read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool read_version(
	ntlm_version *out,
	ntlm_client *ntlm,
	ntlm_buf *message)
{
	return read_byte(&out->major, ntlm, message) &&
		read_byte(&out->minor, ntlm, message) &&
		read_int16(&out->build, ntlm, message) &&
		read_int32(&out->reserved, ntlm, message);
}