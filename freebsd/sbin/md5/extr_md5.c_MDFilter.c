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
struct TYPE_3__ {char* (* End ) (int /*<<< orphan*/ *,char*) ;int /*<<< orphan*/  (* Update ) (int /*<<< orphan*/ *,unsigned char*,unsigned int) ;int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  DIGEST_CTX ;
typedef  TYPE_1__ Algorithm_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int HEX_DIGEST_LENGTH ; 
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned int fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 unsigned int fwrite (unsigned char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 char* stub3 (int /*<<< orphan*/ *,char*) ; 
 char* stub4 (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
MDFilter(const Algorithm_t *alg, int tee)
{
	DIGEST_CTX context;
	unsigned int len;
	unsigned char buffer[BUFSIZ];
	char buf[HEX_DIGEST_LENGTH];

	alg->Init(&context);
	while ((len = fread(buffer, 1, BUFSIZ, stdin))) {
		if (tee && len != fwrite(buffer, 1, len, stdout))
			err(1, "stdout");
		alg->Update(&context, buffer, len);
	}
	printf("%s\n", alg->End(&context, buf));
}