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
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 

__attribute__((used)) static void authenc_request_complete(struct aead_request *req, int err)
{
	if (err != -EINPROGRESS)
		aead_request_complete(req, err);
}