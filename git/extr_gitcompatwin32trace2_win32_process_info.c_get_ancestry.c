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
struct json_writer {int dummy; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 struct json_writer JSON_WRITER_INIT ; 
 int /*<<< orphan*/  TH32CS_SNAPPROCESS ; 
 int /*<<< orphan*/  get_processes (struct json_writer*,scalar_t__) ; 
 int /*<<< orphan*/  jw_array_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_release (struct json_writer*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_data_json (char*,int /*<<< orphan*/ ,char*,struct json_writer*) ; 

__attribute__((used)) static void get_ancestry(void)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot != INVALID_HANDLE_VALUE) {
		struct json_writer jw = JSON_WRITER_INIT;

		jw_array_begin(&jw, 0);
		get_processes(&jw, hSnapshot);
		jw_end(&jw);

		trace2_data_json("process", the_repository, "windows/ancestry",
				 &jw);

		jw_release(&jw);
		CloseHandle(hSnapshot);
	}
}