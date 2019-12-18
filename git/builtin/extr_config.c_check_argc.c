__attribute__((used)) static void check_argc(int argc, int min, int max)
{
	if (argc >= min && argc <= max)
		return;
	if (min == max)
		error(_("wrong number of arguments, should be %d"), min);
	else
		error(_("wrong number of arguments, should be from %d to %d"),
		      min, max);
	usage_builtin_config();
}